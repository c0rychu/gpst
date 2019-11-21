gpst - a gpstime tool
---

- **gpst**

```
$ gpst
Usage: gpst [-n] [-g <gpstime>] [-u <unixtime>] [-h]

        -n --now                 print the current gpstime
        -g --gps <gpstime>       print the unixtime of the gpstime
        -u --unix <unixtime>     print the gpstime of the unixtime
        -h --help                print this message

Expiration date: XXXX-XX-XX   
After this date, it's better to recompile gpst to get new list of leapseconds.
```

- **update_gpst.sh** : update the leap seconds of UTC from https://www.ietf.org/timezones/data/leap-seconds.list

- **util/gpsd.sh**

```
$ gpsd.sh
Usage: gpsd.sh [XXXXX] 
	XXXXX (first 5 digits of gpstime) -- prints the UTC time of it.
	If omitted, it prints the first 5 digits of the current gpstime.
```