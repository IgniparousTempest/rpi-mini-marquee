#!/bin/sh
### BEGIN INIT INFO
# Provides:          rpimm
# Required-Start:    $local_fs $syslog
# Required-Stop:     $local_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Description:       Shows the retropie mini marquee on start and clears on stop.
### END INIT INFO


start() {
  /usr/bin/rpi-mini-marquee -f retropie
  return
}

stop() {
  /usr/bin/rpi-mini-marquee clear
  return
}

uninstall() {
  return
}

case "$1" in
  start)
    start
    ;;
  stop)
    stop
    ;;
  uninstall)
    uninstall
    ;;
  retart)
    stop
    start
    ;;
  *)
    echo "Usage: $0 {start|stop|restart|uninstall}"
esac
exit 0