int main() {
	int c;
	int ret;
	while ((ret = read(0, &c, 1))) {
		putchar(c);
		printf("\n%d\n", ret);
	}
	printf("%d", ret);
}
