import os, sys
limit = 200


if sys.argv[1] == 'r':
	#os.lseek(dev, 0, 0)
	dev = os.open("/dev/myCharDevice", os.O_RDONLY | os.O_NONBLOCK | os.O_EXLOCK)
	try:
		contents = os.read(dev,limit)
		print(contents)
	finally:
		os.close(dev)
elif sys.argv[1] == 'w':
	dev = os.open("/dev/myCharDevice", os.O_WRONLY)
	try:
		data = sys.argv[2]
		if len(data) <= limit:
			data = data + (limit - len(data))*' '
		else:
			data = data[:limit]
		os.write(dev,data)
		print('written ' + data)
	finally:
		os.close(dev)
else:
	print('invalid arg: ' + sys.argv[1])
