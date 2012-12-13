import sys
import os
import pygeoip

gi = pygeoip.GeoIP(os.environ['GEOIP_DATABASE'], pygeoip.MEMORY_CACHE)

for line in sys.stdin:
    if line == '\n' or line[0] == '#':
        continue
    located = 0
    for field in line.split("\t"):
        try:
            record = gi.record_by_addr(field)
        except:
            record = None
        if record is not None:
            located = 1
            break
    if located == 0:
        record = {}
    latitude = record.get('latitude', None)
    longitude = record.get('longitude', None)
    print "%s\t%s\t%s\t%s\t%s\t%s\t%s" % (
        line.strip(),
        record.get('country_code', ''),
        record.get('region_name', ''),
        record.get('city', ''),
        "%0.6f" % latitude if latitude is not None else '',
        "%0.6f" % longitude if longitude is not None else '',
        record.get('postal_code', '')
    )
