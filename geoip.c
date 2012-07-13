#include <GeoIP.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
  GeoIP * gi;
  gi = GeoIP_new(GEOIP_STANDARD);

	char buf[BUFSIZ];
	char capture[BUFSIZ];

	// Loop through stdin
  while ( fgets( buf, sizeof(buf), stdin ) != NULL ) {
  	int i, j = 0, field = 1, located = 0;
  	char *country;

  	// Skip comments and blank lines
  	if (buf[0] == '#' || strlen(buf) == 1) {
  		continue;
  	}

  	// Parse line and collect specified fields
  	if (strlen(buf) > 0) {
	    for (i = 0; i < strlen(buf); i++) {
	    	if (buf[i] == '\t' || buf[i] == '\n') {
	    		capture[j] = '\0';

	    		if (located == 0) {
	    			country = (char*) GeoIP_country_code_by_addr(gi, capture);

	    			if (country != NULL) {
	    				located = 1;
	    			}
	    		}

	    		j = 0;
	    		field++;

	    		if (buf[i] == '\n') {
	    			buf[i] = '\0';
	    		}
	    	} else {
	    		capture[j] = buf[i];
	    		j++;
	    	}
	    }
	  }

  	printf("%s\t%s\n", buf, country);
  }
}