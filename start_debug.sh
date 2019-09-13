if [[ "$OSTYPE" == "darwin"* ]]; then #MacOS
    lldb $1 $2
    #$1 = output artifact, $2 = .evnt file
else #Windows, Linux, FreeBSD, ...
    gdb --args $1 $2
    #$1 = output artifact, $2 = .evnt file
fi