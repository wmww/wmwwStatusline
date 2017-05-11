# WMWW Statusline

__this is currently a work in progress, and as such documentation is incomplete and many things are hard coded that will be configurable__
 
WMWW Statusline is a highly configurable statusline program for Linux. A statusline simply prints out useful information (such as time or resource usage) line-by-line. WMWW Statusline was designed for use with the i3 and sway window managers.

## configuration
I will provide additional documentation later, but this should be all you need to use all current features.

```
version:1

#	config file for WMWW Status
#	this file should go in or be linked from ~/.config/wmww_status.conf

#	if the first non whitespace character in a line is '#', the line is a comment
#	the version thing at the top is not yet used, but may be needed in the future

#	this says to use i3's json protocol (allowing colored output in i3/sway), instead of plaintext.
#	comment this our for human readability or to use WMWW Status in another context
use json

#	when not commented, this constantly reloads the config file for easy configuration.
#	A warning appears so you don't accidentally leave this on (which would cause constant disk reads)
# live reload

#	what fallows is a list of blocks, each which will be one section in the output
{
	#	setting active to false disables this block
	# active: false
	
	#	every block must have a type attribute
	type: ram
	
	#	anything that's like a percentage, can be of style 'h bar', 'v bar' or 'percent' (default)
	style: h bar
	
	#	additionally, 'h bar' can have a bar size (defaults to 1)
	bar size: 4
	
	#	this is the level at which it will turn red (comment out to disable warning)
	warning level: 0.8
}

{
	# active: false
	
	type: cpu
	
	style: v bar
	
	#	this causes the cores to be separated into different meters
	separate cores
}

{
	# active: false
	
	type: time
	
	#	this is a standard UNIX time format
	format: "%a, %b %d"
}

{
	# active: false
	
	#	you can have multiple blocks with the same type
	type: time
	
	format: "%I:%M%P"
}
```

