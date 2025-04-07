#define PY_SSIZE_T_CLEAN
#include <python3.13/Python.h>

#include <string>

#include "IBUS_ENCODER_DECODER/IBUS_FRAME.h"

static PyObject *ibus_Compiler(PyObject *self, PyObject *args) {
  uint16_t ch[14];
  char *dFrame = new char[32];
  if (!PyArg_ParseTuple(args, "iiiiiiiiiiiiiiii", dFrame, dFrame + 1,
                        dFrame + 2, dFrame + 3, dFrame + 4, dFrame + 5,
                        dFrame + 6, dFrame + 7, dFrame + 8, dFrame + 9,
                        dFrame + 10, dFrame + 11, dFrame + 12, dFrame + 13)) {
    return NULL;
  }
  struct IBUS_FRAME frame;
  IBUS_init(&frame);
  IBUS_update_channels(&frame, ch);
  // IBUS_get_frame_to_send(&frame);
  IBUS_get_crc(&frame);

  for (int i = 0; i < 32; i++) {
    dFrame[i] = frame.full_frame[i];
  }

  PyObject *pFrame = PyByteArray_FromStringAndSize(dFrame, 32);
  delete[] dFrame;
  return pFrame;
}

PyMODINIT_FUNC PyInit_ibus(void) {
  static PyMethodDef IbusMethods[] = {
      {"ibus_Compiler", (PyCFunction)ibus_Compiler, METH_VARARGS,
       "Compile the IBUS frame"},
      {NULL, NULL, 0, NULL}};

  static struct PyModuleDef ibusmodule = {PyModuleDef_HEAD_INIT, "_ibus", NULL,
                                          -1, IbusMethods};

  return PyModule_Create(&ibusmodule);
}
