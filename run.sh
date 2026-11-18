IP=$(ip -4 addr | grep -oE '192\.168\.[0-9]+\.[0-9]+' | head -n 1)
cd build
./p $IP "$@"