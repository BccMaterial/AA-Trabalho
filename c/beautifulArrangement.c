int contador;

void backtrack(int pos, int n, int usado[]) {
  if (pos > n) {
    contador++;
    return;
  }

  for (int num = 1; num <= n; num++) {
    if (!usado[num] && (num % pos == 0 || pos % num == 0)) {
      usado[num] = 1;
      backtrack(pos + 1, n, usado);
      usado[num] = 0;
    }
  }
}

int countArrangement(int n) {
  int usado[16] = {0};
  contador = 0;

  backtrack(1, n, usado);

  return contador;
}
