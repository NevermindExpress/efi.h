// Simple amalgamation compiler code. Reads files line-by-line,
// checks for #include's and concatenates them to output file if they
// haven't been included already.
// Line-by-line is inefficient? yes. This code sucks? very likely yes. 
// But what are we doing is dead simple so who cares.
// 
// An idiot admires complexity, a genius admires simplicity.
//							- Terry A. Davis

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

struct file {
	char name[64];
};

struct file files[64] = { 0 };
int nFiles = 0;
FILE* out = NULL;
char line[1024] = "";

void readFile(char* file) {
	FILE* f = fopen(file, "r");

	if (!f) {
		printf("[-] Failed to open %s\n", file);
		exit(1);
	}

	printf("[+] %s\n", file);

	while (fgets(line, 1024, f)) {
		if (!strncmp("#pragma once", line, 12)) // Skip repeating occurrances of #pragma once
			continue;
		else if (line[0] == '\n') // Skip empty lines
			continue;
		else if (!strncmp("#include", line, 8)) {
			// We got an #include, get the included file name
			char* inc = line + 8;
			while (inc[0] == ' ') inc++; // Skip whitespace
			inc++; // Skip " or <
			char* end = line + strlen(line);
			while (end[0] != '\"' && end[0] != '<') {
				end--;
				if (end <= inc) {
					printf("[-] Invalid #include directive \"%s\"", line); exit(1);
				}
			}
			int sz = end - inc;
			// Search whether it'S been included before
			bool found = false;
			for (size_t i = 0; i < nFiles; i++) {
				if (!strncmp(inc, files[i].name, sz)) {
					printf("[*] Already included: \"%.*s\"\n", sz, inc);
					found = true; break;
				}
			}
			if (found) continue;
			// Add file to list
			memcpy(files[nFiles].name, inc, sz); nFiles++;
			// If not, add a comment of file include, open it and concatenate
			fprintf(out, "//%s\n", line);
			readFile(files[nFiles - 1].name);
		} else
			fputs(line, out);
	}
	fputc('\n', out); fclose(f);
}

int main() {
	out = fopen("efi-amalgamation.h", "w");
	if (!out) {
		puts("[-] Failed to open outout file efi-amalgamation.h."); return 1;
	}

	fputs("#pragma once\n", out);
	readFile("efi.h"); 
	fclose(out);
	return 0;
}