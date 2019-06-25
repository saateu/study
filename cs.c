#include <limits.h>
#include <stdio.h>

int add_sat (int x, int y)
{
  int sum = x + y;
  int w = sizeof (int) << 3;
  int sign_x = !!(x >> (w - 1));
  int sign_y = !!(y >> (w - 1));
  int sign_s = !!(sum >> (w - 1));
  int ovf = !(sign_x ^ sign_y) & (sign_x ^ sign_s);
  int p_ovf = sign_s & ovf;
  int n_ovf = !sign_s & ovf;
/*
  printf ("sign_x = %d\n", sign_x);
  printf ("sign_y = %d\n", sign_y);
  printf ("sign_s = %d\n", sign_s);
  printf ("ovf = %d\n", ovf);
  printf ("p_ovf = %d\n", p_ovf);
  printf ("n_ovf = %d\n", n_ovf);

  printf ("sum = %X\n", sum);
  printf ("~(ovf << (w - 1)) = %X\n", ~(ovf << (w - 1)));

  printf ("sum & ~n_ovf & ~p_ovf - %X\n", sum & ~n_ovf & ~p_ovf);
*/

  /* When negative overflow, make INT_MIN */
  sum = (sum & (~0 + n_ovf)) | (n_ovf << (w - 1));

  /* when positive overflow, make INT_MAX */
  sum = (sum & (~0 + p_ovf)) | ((p_ovf << (w - 1)) - p_ovf);

  return sum;
}

int main ()
{
  printf ("%d\n", add_sat (1, 2));
  printf ("%d\n", add_sat (3, -1));
  printf ("%d\n", add_sat (1, 2));
  printf ("%d\n", add_sat (INT_MIN, 0));
  printf ("%d\n", add_sat (INT_MIN, -2));
  printf ("%d\n", add_sat (INT_MIN, INT_MIN));
  printf ("%d\n", add_sat (INT_MIN, INT_MAX));
  printf ("%d\n", add_sat (INT_MAX, 0));
  printf ("%d\n", add_sat (INT_MAX, 1));
  printf ("%d\n", add_sat (INT_MAX, 2));
}
