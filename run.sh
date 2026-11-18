IP="127.0.0.1"
cd build
if [[ $1 == "-i" ]]; then
    IP=$2
    ./p $IP -player2
else
    IP=$(ip -4 addr | grep -oE '192\.168\.[0-9]+\.[0-9]+' | head -n 1)
    echo "Copy this for other device ./run.sh -i $IP"
    ./p $IP
fi