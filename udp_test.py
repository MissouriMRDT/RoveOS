import socket
import struct
import time

# Configurations match the STM32 firmware definitions
LAPTOP_IP = "192.168.0.10"
LAPTOP_PORT = 50001

STM32_IP = "192.168.0.100"
STM32_PORT = 50002

# Layout mapping: 'I' = uint32_t (4 bytes), 'f' = float (4 bytes), '4s' = 4 chars (4 bytes)
PACKET_FORMAT = "<If4s" 

# Set up socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((LAPTOP_IP, LAPTOP_PORT))
sock.settimeout(2.0)

print(f"Listening for STM32 packets on {LAPTOP_IP}:{LAPTOP_PORT}...")

try:
    while True:
        try:
            # 1. RECEIVE & PARSE: Packet from STM32 to Laptop
            data, addr = sock.recvfrom(1024)
            if len(data) == struct.calcsize(PACKET_FORMAT):
                msg_id, sensor_val, status_bytes = struct.unpack(PACKET_FORMAT, data)
                status_str = status_bytes.decode('utf-8').strip('\x00')
                
                print(f"[RECV] From STM32 {addr}: ID={msg_id}, Val={sensor_val:.2f}, Status='{status_str}'")
                
                # 2. SEND: Reverse Packet from Laptop to STM32
                # Send back a packet commanding the LED flag
                response_id = msg_id + 1
                response_val = 99.9
                response_status = b"LED\x00" # matches what STM32 string checks for
                
                tx_data = struct.pack(PACKET_FORMAT, response_id, response_val, response_status)
                sock.sendto(tx_data, (STM32_IP, STM32_PORT))
                print(f" -> [SENT] Reply back to STM32 with 'LED' toggle command.")
                
        except socket.timeout:
            print("Waiting for packet from STM32...")
            
        time.sleep(1)

except KeyboardInterrupt:
    print("\nStopping UDP application.")
    sock.close()