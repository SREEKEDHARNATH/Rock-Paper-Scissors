IP="127.0.0.1"
echo "Make sure you are connected to internet"
wget "https://github.com/SREEKEDHARNATH/Rock-Paper-Scissors/releases/download/v1.0/Rock-Paper-Scissors.AppImage"
if [[ $? -eq 0 ]]; then
    FLAGS=" "
    chmod +x Rock-Paper-Scissors.AppImage
    if [[ $1 == "-i" ]]; then
        IP=$2
        FLAGS="$IP -player2"
    else
        IP=$(ip -4 addr | grep -oE '192\.168\.[0-9]+\.[0-9]+' | head -n 1)
        echo "Copy this for other device ./run.sh -i $IP"
        FLAGS="$IP"
    fi
    ./Rock-Paper-Scissors.AppImage $FLAGS
else 
    echo "Appimage download failed"
fi
