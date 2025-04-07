#define PY_SSIZE_T_CLEAN
#include <python3.13/Python.h>

#include <string>

#include "IBUS_ENCODER_DECODER/IBUS_FRAME.h"

static PyObject *ibus_Compiler(PyObject *self, PyObject *args) {
  uint16_t ch[14];
  char *dFrame = new char[32];
  if (!PyArg_ParseTuple(args, "iiiiiiiiiiiiii", ch, ch + 1, ch + 2, ch + 3,
                        ch + 4, ch + 5, ch + 6, ch + 7, ch + 8, ch + 9, ch + 10,
                        ch + 11, ch + 12, ch + 13)) {
    return NULL;
  }
  struct IBUS_FRAME frame;
  IBUS_init(&frame);
  IBUS_update_channels(&frame, ch);
  IBUS_get_frame_values(&frame);
  // IBUS_get_crc(&frame);

  for (int i = 0; i < 32; i++) {
    dFrame[i] = frame.full_frame[i];
  }

  PyObject *pFrame = PyByteArray_FromStringAndSize(dFrame, 32);
  delete[] dFrame;
  return pFrame;
}

PyMODINIT_FUNC PyInit__ibus(void) {
  static PyMethodDef IbusMethods[] = {
      {"ibus_Compiler", (PyCFunction)ibus_Compiler, METH_VARARGS,
       "Compile the IBUS frame"},
      {NULL, NULL, 0, NULL}};

  static struct PyModuleDef ibusmodule = {PyModuleDef_HEAD_INIT, "_ibus", NULL,
                                          -1, IbusMethods};

  return PyModule_Create(&ibusmodule);
}
