# geoip

A command-line interface to the MaxMind GeoIP database for use with tab delimited files. Uses the [MaxMind C API](http://www.maxmind.com/app/c).

## Usage

	geoip -f[fields] <infile >outfile

fields - a comma separated list of fields which contain hosts to reverse, in order. Once one has been successfully reversed, the rest will not be checked.

Example invocation:

	geoip -f2 <infile >outfile

Example input:

	Google	173.194.37.64	Some other text

Example output:

	Google	173.194.37.64	Some other text	US