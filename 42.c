#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Bracket {
	char brac;
	int line;
	char f;
	struct Bracket* next;
} ele;
int isBrac (int B);

int main () {

	////���룻
	FILE *in = fopen ("example.c","r");
	ele *start = (ele*)malloc (sizeof (ele)), *end = start;
	char c, t;
	int l = 1, count = 0;
	while (~ (c = fgetc (in))) {
		//�ַ�������
		if ((c == '\''))
			while ((c = fgetc (in)) != '\'');
		//�ַ�������
		if ((c == '\"'))
			while ((c = fgetc (in)) != '\"');
		//ע��(���У�
		if ((c == '/') && c == t)
			while (((c = fgetc (in)) != '\n'));
		//ע�ͣ����У�
		if ((t == '/') && (c == '*'))
			while (~ (c = fgetc (in))) {
				if ((t == '*') && (c == '/')) {
					break;
				}
				if ((c == '\n'))
					l ++;
				t = c;
			}
		//������ջ
		if (isBrac (c)) {
			//printf ("%c",c);
			end -> brac = c;
			count ++;
			end -> line = l;
			end -> f = 1;
			end -> next = (ele*)malloc (sizeof (ele));
			end = end -> next;
		}
		//���棬����
		if ((c == '\n') )
			l ++;

		t = c;
	}
	fclose (in);
	end -> f = 0;
	end -> next = NULL;

	////ƥ�䣻
	ele *judge, *top, *ne, *be;
	while (count > 1) {
		//��ʼ��
		//ջ��&&����
		for (top = start; top != NULL; top = top -> next) {
			if (((top -> brac == '(') || (top -> brac == '{')) && top -> f)
				judge = top;
			if (((top -> brac == ')') || (top -> brac == '}')) && top -> f) {
				ne = top;
				break;
			}
		}
		//ǰ��
		for (top = start, be = end; top != judge; top = top -> next) {
			if (((top -> brac == '(') || (top -> brac == '{')) && top -> f)
				be = top;
		}
		//����
		if (judge -> brac == '{') {
			//ǰ��ƥ�䣻
			if (be -> brac == '(') {
				printf ("without maching '%c' at line %d", be -> brac, be -> line);
				return 0;
			}
			//��ƥ�䣻
			if (ne -> brac == ')') {
				printf ("without maching '%c' at line %d", ne -> brac, ne -> line);
				return 0;
			}
		}
		if (judge -> brac == '(') {
			//��ƥ�䣻
			if (ne -> brac == '}') {
				printf ("without maching '%c' at line %d", ne -> brac, ne -> line);
				return 0;
			}
		}
		//ƥ��
		judge -> f = 0, ne -> f = 0;
		count -= 2;
	}

	////δƥ��
	if (count) {
		for (top = start; top != NULL; top = top -> next)
			if (top -> f)
				printf ("without maching '%c' at line %d", top -> brac, top -> line);;

	} else
		//ȫƥ��
		for (top = start; top != NULL; top = top -> next)
			printf ("%c",top -> brac);
	return 0;
}

int isBrac(int B) {
	if (B == '{' ||B == '}'||B == '(' ||B == ')')
		return 1;
	return 0;
}


