#!/bin/bash
#leaps2cpp.sh
#Generate leaps_gps.h

rawleaps=$(curl https://data.iana.org/time-zones/data/leap-seconds.list)
unix0_in_ntp=2208988800  # 1970-1900 in ntp seconds

expire=$(( $(awk '/^#@/ {print $2}' <(echo "$rawleaps")) - $unix0_in_ntp ))  # expired time in unix-timestemps
case $(uname -s) in
    'Linux')
        expStr=$(date -ud @$expire '+%Y-%m-%d')
        ;;
    'Darwin')
        expStr=$(date -ur $expire '+%Y-%m-%d')
        ;;
esac

leaps=$(awk -v t0=$unix0_in_ntp '!/^#/ {print $1-t0}' <<<"$rawleaps" |sed '1,10d')
nleaps=$(awk '{ ++count } END{ print count }' <<<"$leaps")

( printf "/* Automatically converted from https://data.iana.org/time-zones/data/leap-seconds.list */\n"\
; printf "#ifndef GPST_LEAPS \n"\
; printf "#define GPST_LEAPS \n"\
; printf "#define EXPIRE_ON $expire\n"\
; printf "#define EXPIRE_ON_STR \"$expStr\"\n"\
; printf "#define N_LEAPS $nleaps\n"\
; printf "const time_t leaps[]={"\
; awk '{printf "%lu," ,$1}' <<<"$leaps"\
; printf "};\n"\
; printf "\n/*---------- Source Code ------------*/\n"\
; sed 's:^://  :' update_gpst.sh\
; printf "#endif"\
)|cat > include/gpst_leaps.h
