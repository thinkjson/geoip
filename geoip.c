#include "GeoIP.h"
#include "GeoIPCity.h"
#include <stdio.h>

static const char * _mk_NA( const char * p ){
 return p ? p : "";
}

int main (int argc, char *argv[]) {
  GeoIP * gi;
  GeoIPRecord * record;
  char * database = getenv("GEOIP_DATABASE");
  if (database == NULL) {
    fprintf(stderr, "The GEOIP_DATABASE must be set to the location of a GeoIP City database.");
    exit(1);
  } else {
    gi = GeoIP_open(database, GEOIP_MEMORY_CACHE);
  }

  char buf[BUFSIZ];
  char capture[BUFSIZ];

  // Loop through stdin
  while ( fgets( buf, sizeof(buf), stdin ) != NULL ) {
    int i, j = 0, k = 0, periods = 0, field = 1, located = 0;

    // Skip comments and blank lines
    if (buf[0] == '#' || strlen(buf) == 1) {
      continue;
    }

    // Parse line and collect specified fields
    if (strlen(buf) > 0) {

      // Iterate over characters in line capturing field by field
      for (i = 0; i < strlen(buf); i++) {

        // Look for field or line ending
        if (buf[i] == '\t' || buf[i] == '\n') {
          // Terminate capture
          capture[j] = '\0';

          // Try to geolocate capture
          if (located == 0 && strlen(capture) > 0) {
            // See how many periods it has
            periods = 0;
            for (k = 0; k < strlen(capture); k++) {
              if (capture[k] == '.') {
                periods++;
              }
            }

            // If it looks like an IPv4 address, geolocate it
            if (periods == 3) {
              record = GeoIP_record_by_name(gi, (const char *) capture);

              // If we have a match, mark line as located
              if (record != NULL) {
                located = 1;
              }
            }
          }

          // Reset field position
          j = 0;
          field++;

          // Strip newlines from fields
          if (buf[i] == '\n') {
            buf[i] = '\0';
          }
        } else {
          capture[j] = buf[i];
          j++;
        }
      }
    }

    // Print out line, and located information
    if (record != NULL) {
      printf("%s\t%s\t%s\t%s\t%f\t%f\t%s\n", buf,
        _mk_NA(record->country_code),
        _mk_NA(record->region),
        _mk_NA(record->city),
        record->latitude,
        record->longitude,
        _mk_NA(record->postal_code));

      GeoIPRecord_delete(record);
    } else {
      printf("%s\t\t\t\t\t\t\n", buf);
    }
  }
}