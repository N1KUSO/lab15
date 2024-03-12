#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

typedef struct matrix {
    int **values;
    int nRows;
    int nCols;
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d\t", m.values[i][j]);
        }
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2) {
    assert(i1 >= 0 && i1 < m.nRows && i2 >= 0 && i2 < m.nRows);

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    assert(j1 >= 0 && j1 < m.nCols && j2 >= 0 && j2 < m.nCols);

    for (int i = 0; i < m.nRows; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *criteriaValues = (int *) malloc(m.nRows * sizeof(int));

    for (int i = 0; i < m.nRows; i++) {
        criteriaValues[i] = criteria(m.values[i], m.nCols);
    }

    for (int i = 1; i < m.nRows; i++) {
        int key = criteriaValues[i];
        int *tempRow = m.values[i];
        int j = i - 1;

        while (j >= 0 && criteriaValues[j] > key) {
            criteriaValues[j + 1] = criteriaValues[j];
            m.values[j + 1] = m.values[j];
            j--;
        }

        criteriaValues[j + 1] = key;
        m.values[j + 1] = tempRow;
    }

    free(criteriaValues);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    for (int i = 0; i < m.nCols; i++) {
        int minColIndex = i;
        for (int j = i + 1; j < m.nCols; j++) {
            if (criteria(m.values[j], m.nRows) < criteria(m.values[minColIndex], m.nRows)) {
                minColIndex = j;
            }
        }

        if (minColIndex != i) {
            for (int k = 0; k < m.nRows; k++) {
               swapColumns(m, k, minColIndex);
            }
        }
    }
}

#endif
