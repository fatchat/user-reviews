package main

import (
	"regexp"
    "fmt"
	"os"
	"io"
	"log"
	"bufio"
)

// field names
var field_names = []string {"Summary", "Date", "Type", "Description", "Reviewer ID", "Item", "Item Name",
	"Item URL", "Item Photo", "Context"}

func main () {

	// parse cmdline arguments
	verbose := false
	inputfile := ""
	args := os.Args
	if len (args) < 2 {
		fmt.Printf ("usage: %s [--verbose] <input file>\n", args[0])
		return
	}
	if len (args) == 2 {
		inputfile = args[1]
	}
	if len (args) == 3 {
		if args[1] == "--verbose" || args[1] == "-v" {
			verbose = true
		}
		inputfile = args[2]
	}

	// build the regexp object
	regex_expression := `,("[^"]*(?:"|$))?`
	regex, error := regexp.Compile (regex_expression)
	if error != nil {
     	log.Fatal (error)
	}

	// open the input file
	f, error := os.Open (inputfile)
	if error != nil {
     	log.Fatal (error)
	}

	// construct a file reader
	reader := bufio.NewReader (f)

	// is_prefix means the entire line did not fit into the buffer
	line, is_prefix, error := reader.ReadLine ()
	
	for line != nil && !is_prefix {

		// print the input if the user requested it
		if verbose {
			fmt.Printf ("read [%s]\n", line)
		}

		// match against the regex
		matches := regex.FindAll (line, -1)
		for index, match := range matches {

			// trim the leading comma
			match = match[1:]

			// only print if there was something at this position
			if len(match) > 0 {
	     		fmt.Printf ("%s => %s\n", field_names[index], match)
			}
		}

		fmt.Println ("===========================================================")

		// read next line
		line, is_prefix, error = reader.ReadLine ()
	}
	
	// did not read entire line due to small buffer
	if is_prefix {
      	log.Fatal ("buffer too small!")
	}

	// error other than EOF
	if error != nil && error != io.EOF {
		fmt.Println ("Error: exited loop")
      	log.Fatal (error)
	}
	
}
