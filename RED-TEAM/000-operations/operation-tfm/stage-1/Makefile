
all: 
	python3 cdn/http-server.py &
	nc -lvnp 4444

clean:
	pkill -f http-server.py
