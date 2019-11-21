#!/bin/bash
#gpsd.sh

main(){
    if [ $# -eq 0 ]; then
        echo $(gpst -n |cut -c1-5)
    else
        unix2utc $(gpst -g $100000)
    fi
}

unix2utc()
{
    case $(uname -s) in
        'Linux')
            echo $(date -ud @$1 '+%Y-%m-%d %H:%M:%S') UTC
            ;;
        'Darwin')
            echo $(date -ur $1 '+%Y-%m-%d %H:%M:%S') UTC
            ;;
    esac
}

main $@
