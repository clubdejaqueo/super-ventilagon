struct TunableItem {
  int& value;
  char* name;
  TunableItem(int& value, char* name) : value(value), name(name) {}
};

#define DEF_ITEM(x) TunableItem(x, #x)

TunableItem ti[] = {
  DEF_ITEM(nave_calibrate),
};

const int num_tunableitems = elements_in(ti);

int selected_tunable = 0;

void finetune_plus() {
  ti[selected_tunable].value++;
}

void finetune_minus() {
  ti[selected_tunable].value--;
}

void finetune_next() {
  selected_tunable = (selected_tunable + 1) % num_tunableitems;
  for (int n = 0; n < num_tunableitems; n++) {
    if (n == selected_tunable) {
      debug(">>> ");
    }
    debug(ti[selected_tunable].name);
    debug(": ");
    debugln(ti[selected_tunable].value);
  }
}
