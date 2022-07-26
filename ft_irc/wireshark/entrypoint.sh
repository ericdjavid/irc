git clone https://github.com/linuxserver/docker-wireshark.git
cd docker-wireshark
docker build \
  --no-cache \
  --pull \
  -t lscr.io/linuxserver/wireshark:latest .