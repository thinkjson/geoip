# geoip

A command-line interface to the MaxMind GeoIP database for use with tab delimited files. It reads fields from left to right, attempting to geolocate the contents of the field, and appends a field to the end with the first match. Requires the [MaxMind C API](http://www.maxmind.com/app/c).

## Installation

First ensure you have the MaxMind C API installed:

	apt-get install libgeoip-dev

Then just clone and make:

	git clone git://github.com/thinkjson/geoip.git
	cd geoip
	make
	make install

## Usage

	geoip <infile >outfile

Example input:

	Google	173.194.37.64	Some other text

Example output:

	Google	173.194.37.64	Some other text	US