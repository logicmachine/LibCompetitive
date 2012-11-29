# -*- coding: utf-8 -*-

import sys
import os
import re
from optparse import OptionParser

parser = OptionParser("Usage: %prog [options] filename")
parser.add_option("-l", "--line", dest = "line",
                  default = False, action = "store_true",
                  help = "insert #line directive to generated code")
parser.add_option("-u", "--using", dest = "using",
                  default = "", metavar = "ns",
                  help = "insert \"using namespace ns;\" to generated code")
parser.add_option("-d", "--dir", dest = "directory",
                  default = ".",  metavar = "directory",
                  help = "set root directory of user library")
(options, args) = parser.parse_args()
if(len(args) != 1):
	parser.print_help()
	sys.exit()

re_pragma_once = re.compile('^\#\s*pragma\s+once')
re_common_include = re.compile('^\#\s*include\s<([^>]*)>')
re_user_include = re.compile('^\#\s*include\s"([^"]*)"')

def get_next_file(current, filename):
	if os.path.exists(filename):
		return os.path.abspath(filename)
	name = os.path.join(options.directory, filename)
	if os.path.exists(name):
		return os.path.abspath(name)
	name = os.path.join(os.path.dirname(current), filename)
	if os.path.exists(name):
		return os.path.abspath(name)
	return os.path.abspath(filename)

def load_file(filename, included, standards):
	line_number = 0
	lines = []
	pragma_once = False
	for line in open(filename, 'r'):
		line_number += 1
		if not re_pragma_once.match(line) is None:
			if filename in included:
				return []
			included.append(filename)
			continue
		match_common = re_common_include.match(line)
		if not match_common is None:
			standards.append(match_common.group(1))
			continue
		match_user = re_user_include.match(line)
		if not match_user is None:
			next_file = get_next_file(filename, match_user.group(1))
			lines.extend(load_file(next_file, included, standards))
			continue
		lines.append((filename, line_number, line))
	return lines

standard_libraries = []
included = []
lines = load_file(args[0], included, standard_libraries)
if options.line:
	print "#line 1 \"include-section\""
for name in set(standard_libraries):
	print "#include <%s>" % name
if options.using != '':
	print "using namespace %s;" % options.using
prev_filename = ""
prev_line = -1
for line in lines:
	if options.line and (prev_filename, prev_line + 1) != (line[0], line[1]):
		print "#line %d \"%s\"" % (line[1], line[0])
	(prev_filename, prev_line) = (line[0], line[1])
	sys.stdout.write("%s" % line[2])

