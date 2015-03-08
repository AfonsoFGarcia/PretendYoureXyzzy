#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>

int id = 1000000;
FILE *blacks;
FILE *whites;
FILE *sqlfile;

void parse_blacks() {
	char buf[256];
	char c = fgetc(blacks);
	int i = 0;
	int picks = 0;
	
	while(c != EOF) {
		if (c == '\r') {
			// DO NOTHING
		} else if (c == '\n') {
			buf[i] = '\0';
			i = 0;
			fprintf(sqlfile, "INSERT INTO black_cards VALUES (%d, '%s', 0, %d, NULL);\n", ++id, buf, (picks == 0 ? 1 : picks/4));
			fprintf(sqlfile, "INSERT INTO card_set_black_card VALUES (1000000, %d);\n", id);
			picks = 0;
		} else if (c == '_') {
			picks++;
			buf[i++] = c;
		} else if (c == '\'') {
			buf[i++] = c;
			buf[i++] = c;
		} else {
			buf[i++] = c;
		}
		c = fgetc(blacks);
	}
}

void parse_whites() {
	char buf[256];
	char c = fgetc(whites);
	int i = 0;
	
	while(c != EOF) {
		if (c == '\r') {
			// DO NOTHING
		} else if (c == '\n') {
			buf[i] = '\0';
			i = 0;
			fprintf(sqlfile, "INSERT INTO white_cards VALUES (%d, '%s', NULL);\n", ++id, buf);
			fprintf(sqlfile, "INSERT INTO card_set_white_card VALUES (1000000, %d);\n", id);
		} else if (c == '\'') {
			buf[i++] = c;
			buf[i++] = c;
		} else {
			buf[i++] = c;
		}
		c = fgetc(whites);
	}
}

int main(int argc, char** argv) {
	if(argc != 4) {
		printf("Usage: cardparser [black cards] [white cards] [sql file]\n");
		return 1;
	}

	blacks = fopen(argv[1], "r");
	whites = fopen(argv[2], "r");
	sqlfile = fopen(argv[3], "w");
	
	if(blacks == NULL) {
		printf("Invalid black cards file!\n");
		return 2;
	}
	if(whites == NULL) {
		printf("Invalid white cards file!\n");
		return 3;
	}
	if(sqlfile == NULL) {
		printf("Invalid sql file!\n");
		return 4;
	}

	fprintf(sqlfile, "INSERT INTO card_set VALUES (1000000, true, 'Twitter', true, 'Porque o CAH não era mau que chegue.', 4);\n");

	parse_blacks();
	parse_whites();

	fclose(blacks);
	fclose(whites);
	fclose(sqlfile);
}
