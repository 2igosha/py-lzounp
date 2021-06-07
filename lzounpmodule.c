/*
 * =====================================================================================
 *       Filename:  lzounpmodule.c
 *    Description: LZO bindings for Python3 
 *        Created:  07.06.2021 15:09:25
 *         Author:  Igor Kuznetsov (igosha), 2igosha@gmail.com
 * =====================================================================================
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <lzo/lzo1x.h>
#include <lzo/lzo1y.h>
#include <lzo/lzo1z.h>

static PyObject *
lzounp_lzo1z_decompress(PyObject *self, PyObject *args)
{
    Py_buffer compressed;
    if (!PyArg_ParseTuple(args, "y*", &compressed))
        return NULL;
    lzo_uint	lenOut = compressed.len*10;
    unsigned char* dataOut = malloc(lenOut);
    int result = lzo1z_decompress_safe(compressed.buf, compressed.len, dataOut, &lenOut, NULL);
    if ( result != 0 ) {
        free(dataOut);
        return PyErr_Format(PyExc_RuntimeError, "lzo1z_decompress_safe returned %d", result);
    }
    PyObject* ret = PyBytes_FromStringAndSize((const char*)dataOut, lenOut);
    free(dataOut);
    return ret;
}


static PyObject *
lzounp_lzo1y_decompress(PyObject *self, PyObject *args)
{
    Py_buffer compressed;
    if (!PyArg_ParseTuple(args, "y*", &compressed))
        return NULL;
    lzo_uint	lenOut = compressed.len*10;
    unsigned char* dataOut = malloc(lenOut);
    int result = lzo1y_decompress_safe(compressed.buf, compressed.len, dataOut, &lenOut, NULL);
    if ( result != 0 ) {
        free(dataOut);
        return PyErr_Format(PyExc_RuntimeError, "lzo1x_decompress_safe returned %d", result);
    }
    PyObject* ret = PyBytes_FromStringAndSize((const char*)dataOut, lenOut);
    free(dataOut);
    return ret;
}


static PyObject *
lzounp_lzo1x_decompress(PyObject *self, PyObject *args)
{
    Py_buffer compressed;
    if (!PyArg_ParseTuple(args, "y*", &compressed))
        return NULL;
    lzo_uint	lenOut = compressed.len*10;
    unsigned char* dataOut = malloc(lenOut);
    int result = lzo1x_decompress_safe(compressed.buf, compressed.len, dataOut, &lenOut, NULL);
    if ( result != 0 ) {
        free(dataOut);
        return PyErr_Format(PyExc_RuntimeError, "lzo1x_decompress_safe returned %d", result);
    }
    PyObject* ret = PyBytes_FromStringAndSize((const char*)dataOut, lenOut);
    free(dataOut);
    return ret;
}


static PyMethodDef LzounpMethods[] = {
    {"lzo1z_decompress",  lzounp_lzo1z_decompress, METH_VARARGS,
     "Decompress LZO1Z."},
    {"lzo1y_decompress",  lzounp_lzo1y_decompress, METH_VARARGS,
     "Decompress LZO1Y."},
    {"lzo1x_decompress",  lzounp_lzo1x_decompress, METH_VARARGS,
     "Decompress LZO1X."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef lzounpmodule = {
    PyModuleDef_HEAD_INIT,
    "lzounp",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    LzounpMethods
};

PyMODINIT_FUNC
PyInit_lzounp(void)
{
    return PyModule_Create(&lzounpmodule);
}

