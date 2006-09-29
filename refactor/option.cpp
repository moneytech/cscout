/*
 * (C) Copyright 2006 Diomidis Spinellis.
 *
 * A user interface option
 *
 * $Id: option.cpp,v 1.3 2006/09/29 18:20:56 dds Exp $
 */

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>		// max
#include <cstdio>		// FILE, stderr
#include <cstdlib>		// atoi
#include <cstdarg>
#include <cctype>

#include "swill.h"
#include "getopt.h"

#include "cpp.h"
#include "debug.h"
#include "error.h"
#include "option.h"


BoolOption *Option::fname_in_context;		// Remove common file prefix
BoolOption *Option::show_true;			// Only show true identifier properties
BoolOption *Option::show_line_number;		// Annotate source with line numbers
BoolOption *Option::file_icase;			// File name case-insensitive match
BoolOption *Option::sort_rev;			// Reverse sorting of query results
BoolOption *Option::show_projects;		// Show associated projects
BoolOption *Option::show_identical_files;	// Show a list of identical files
IntegerOption *Option::tab_width;		// Tab width for code output
SelectionOption *Option::cgraph_type;		// Call graph type t(text h(tml d(ot s(vg g(if
SelectionOption *Option::cgraph_show;		// Call graph show e(dge n(ame f(ile p(ath
TextOption *Option::sfile_re_string;		// Saved files replacement location RE string
TextOption *Option::sfile_repl_string;		// Saved files replacement string
IntegerOption *Option::entries_per_page;		// Number of elements to show in a page
vector<Option *> Option::options;		// Options in the order they were added
map<string, Option *> Option::omap;		// For loading options

SelectionOption::SelectionOption(const char *sn, const char *un, char iv, ...) :
	Option(sn, un), v(iv)
{
	va_list marker;
	va_start(marker, iv);
	for (;;) {
		const char *s = va_arg(marker, const char *);
		if (s == NULL)
			break;
		options.push_back(SelectionElement(s));
	}
	va_end(marker);
}

void
SelectionOption::display(FILE *f)
{
	fprintf(f, "<tr><td>%s</td><td>", user_name);
	for (vector <SelectionElement>::const_iterator i = options.begin(); i != options.end(); i++)
		fprintf(f, "<input type=\"radio\" name=\"%s\" value=\"%c\" %s>%s\n",
			short_name,
			i->c,
			v == i->c ? "checked" : "",
			i->name);
	fputs("</td></tr>\n", f);
}

void
TextOption::load(ifstream &ifs)
{
	getline(ifs, v);
	// Skip leading whitespace
	while (v.length() && isspace(v[0]))
		v.erase(v.begin());
}

// Add a new option to the pool
void
Option::add(Option *o)
{
	options.push_back(o);
	omap[o->short_name] = o;
}

// Save to a file
void
Option::save_all(ofstream &ofs)
{
	for (vector <Option *>::const_iterator i = options.begin(); i != options.end(); i++) {
		ofs << (*i)->short_name << ": ";
		(*i)->save(ofs);
		ofs << endl;
	}
}

// Load from a file
void
Option::load_all(ifstream &in)
{
	while (!in.eof()) {
		string val;
		in >> val;
		if (val.empty())
			continue;
		map<string, Option *>::const_iterator i;
		if ((i = omap.find(val.substr(0, val.length() - 1))) != omap.end())
			i->second->load(in);
		else
			cerr << "Skipping unknown option :" << val << endl;
	}
}

// Set from a submitted page
void
Option::set_all()
{
	for (vector <Option *>::const_iterator i = options.begin(); i != options.end(); i++)
		(*i)->set();
}

// Display on a web page
void
Option::display_all(FILE *f)
{
	fputs("<table>", f);
	for (vector <Option *>::const_iterator i = options.begin(); i != options.end(); i++)
		(*i)->display(f);
	fputs("</table>", f);
}


// Initialize the option objects and their container
void
Option::initialize()
{
	Option::add(new TitleOption("File and Identifier Pages"));
	Option::add(show_true = new BoolOption("show_true", "Show only true identifier classes (brief view)"));
	Option::add(show_projects = new BoolOption("show_projects", "Show associated projects", true));
	Option::add(show_identical_files = new BoolOption("show_identical_files", "Show a list of identical files", true));

	Option::add(new TitleOption("Source Listings"));
	Option::add(show_line_number = new BoolOption("show_line_number", "Show line numbers"));
	Option::add(tab_width = new IntegerOption("tab_width", "Tab width", 8));

	Option::add(new TitleOption("Queries"));
	Option::add(file_icase = new BoolOption("file_icase", "Case-insensitive file name regular expression match"));

	Option::add(new TitleOption("Query Result Lists"));
	Option::add(entries_per_page = new IntegerOption("entries_per_page", "Number of entries on a page", 50));
	Option::add(fname_in_context = new BoolOption("fname_in_context", "Show file lists with file name in context"));
	Option::add(sort_rev = new BoolOption("sort_rev", "Sort identifiers starting from their last character"));

	Option::add(new TitleOption("Call Graphs"));
	Option::add(cgraph_type = new SelectionOption("cgraph_type", "Call graph links should lead to pages of:", 'h',
		"t:plain text",
		"h:HTML",
		"d:dot",
		"s:SVG (via dot)",
		"g:GIF (via dot)",
		NULL));
	Option::add(cgraph_show = new SelectionOption("cgraph_show", "Call graphs should contain:", 'f',
		"e:only edges",
		"n:function names",
		"f:file and function names",
		"p:path and function names",
		NULL));

	Option::add(new TitleOption("Saved Files"));
	Option::add(sfile_re_string = new TextOption("sfile_re_string", "When saving modified files replace RE"));
	Option::add(sfile_repl_string = new TextOption("sfile_repl_string", "... with the string"));
}
