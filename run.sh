IP="127.0.0.1"
cd build
echo "Make sure you are connected to internet"
if [[ $? -eq 0 ]]; then
    FLAGS=" "
    if [[ $1 == "-i" ]]; then
        IP=$2
        FLAGS="$IP -player2"
    else
        IP=$(ip -4 addr | grep -oE '192\.168\.[0-9]+\.[0-9]+' | head -n 1)
        echo "Copy this for other device ./run.sh -i $IP"
        FLAGS="$IP -player2"
    fi
    ./p $FLAGS
else 
    echo "Build folder not exist"
fi