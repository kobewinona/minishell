#!/usr/bin/python3
import time
import os


print(f"[PID: {os.getpid()}]Start script")
for i in range(15):
	print(f"[{i} sec] Doing task...")
	time.sleep(0.3)
