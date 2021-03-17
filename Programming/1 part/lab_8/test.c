#include <stdio.h>

int main()
{
	/* задание 3 */

	enum {
		ready,
		low_toner,
		drum_damaged,
		no_paper
	};
	int bit_field = ready | low_toner | drum_damaged | no_paper;
	int laser_printer;
	printf("State of laser printer: ");
	scanf("%d", &laser_printer);
	laser_printer = laser_printer & bit_field;
	printf("Ready: %s\n", laser_printer & ready ? "yes" : "no");
	printf("Low toner: %s\n", laser_printer & low_toner ? "yes" : "no");
	printf("drum_damaged: %s\n", laser_printer & drum_damaged ? "yes" : "no");
	printf("no_paper: %s\n", laser_printer & no_paper ? "yes" : "no");
    return 0;
}

