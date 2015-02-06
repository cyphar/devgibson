#!/usr/bin/env python2
import sys

with open(sys.argv[1], "rb") as f:
	person = None
	text = ""

	for line in f:
		if person is None and not line.startswith(" "*32):
			# Not even start of dialogue
			continue

		if line.startswith(" "*32 + "("):
			# Skip scene direction.
			continue

		if line.startswith(" "*32) and line.strip().endswith(")"):
			# Skip more scene direction.
			continue

		if line.startswith(" "*32):
			# Start dialogue
			person = line.strip()
			continue

		if line.startswith(" "*20):
			# Some dialogue
			text += " " + line.strip()
			continue

		if line.strip() == "":
			# End dialogue
			print("<{0}> {1}".format(person, text.strip()))
			person = None
			text = ""
			continue
