#include <stdio.h>
#include "libs/matrix.h"

void testSwap() {
    int values[] = {1,2,3,4,5,6,7,8,9};
    matrix test = createMatrixFromArray(values,3,3);

    swapRows(&test, 0, 2);
    assert(test.values[0][0] == 7 && test.values[0][1] == 8 && test.values[0][2] == 9);
    assert(test.values[2][0] == 1 && test.values[2][1] == 2 && test.values[2][2] == 3);

    freeMemMatrix(&test);
    matrix test2 = createMatrixFromArray(values,3,3);

    swapColumns(&test2, 0, 2);
    assert(test2.values[0][0] == 3 && test2.values[0][1] == 2 && test2.values[0][2] == 1);
    assert(test2.values[1][0] == 6 && test2.values[1][1] == 5 && test2.values[1][2] == 4);

    freeMemMatrix(&test2);
}

int getSum_(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

void testSortFunctions() {
    int values[] = {10, 12, 3, 4, 5, 6, 0, 8, 9};
    matrix testMatrix = createMatrixFromArray(values, 3, 3);

    insertionSortRowsMatrixByRowCriteria(testMatrix, getSum_);
    assert(testMatrix.values[0][0] == 4 && testMatrix.values[0][1] == 5 && testMatrix.values[0][2] == 6);
    assert(testMatrix.values[1][0] == 0 && testMatrix.values[1][1] == 8 && testMatrix.values[1][2] == 9);

    selectionSortColsMatrixByColCriteria(testMatrix, getSum_);
    assert(testMatrix.values[0][0] == 4 && testMatrix.values[0][1] == 5 && testMatrix.values[0][2] == 6);
    assert(testMatrix.values[1][0] == 0 && testMatrix.values[1][1] == 8 && testMatrix.values[1][2] == 9);

    freeMemMatrix(&testMatrix);
}

void testIsSquareMatrix() {
    int values1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix testMatrix1 = createMatrixFromArray(values1, 3, 3);

    int values2[] = {1, 2, 3, 4, 5};
    matrix testMatrix2 = createMatrixFromArray(values2, 2, 3);

    assert(isSquareMatrix(&testMatrix1));
    assert(!isSquareMatrix(&testMatrix2));

    freeMemMatrix(&testMatrix1);
    freeMemMatrix(&testMatrix2);
}

void testAreTwoMatricesEqual() {
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix testMatrix1 = createMatrixFromArray(values, 3, 3);
    matrix testMatrix2 = createMatrixFromArray(values, 3, 3);

    int values4[] = {1, 2, 3, 4};
    matrix testMatrix3 = createMatrixFromArray(values4, 2, 2);

    assert(areTwoMatricesEqual(&testMatrix1, &testMatrix2));
    assert(!areTwoMatricesEqual(&testMatrix1, &testMatrix3));

    freeMemMatrix(&testMatrix1);
    freeMemMatrix(&testMatrix2);
    freeMemMatrix(&testMatrix3);
}

void testIsEMatrix() {
    int valuesIdentity[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    matrix identityMatrix = createMatrixFromArray(valuesIdentity, 3, 3);

    assert(isEMatrix(&identityMatrix));

    freeMemMatrix(&identityMatrix);
}

void testIsSymmetricMatrix() {
    int valuesSymmetric[] = {1, 2, 3, 2, 4, 5, 3, 5, 6};
    matrix symmetricMatrix = createMatrixFromArray(valuesSymmetric, 3, 3);

    int valuesNonSymmetric[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix nonSymmetricMatrix = createMatrixFromArray(valuesNonSymmetric, 3, 3);


    assert(isSymmetricMatrix(&symmetricMatrix));
    assert(!isSymmetricMatrix(&nonSymmetricMatrix));

    freeMemMatrix(&symmetricMatrix);
    freeMemMatrix(&nonSymmetricMatrix);
}

void testGetMinAndMaxValuePos() {
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix testMatrix = createMatrixFromArray(values, 3, 3);

    position minPos = getMinValuePos(testMatrix);
    position maxPos = getMaxValuePos(testMatrix);
    assert(minPos.rowIndex == 0 && minPos.colIndex == 0);
    assert(maxPos.rowIndex == 2 && maxPos.colIndex == 2);

    freeMemMatrix(&testMatrix);
}

void testTransposeSquareMatrix() {
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix testMatrix = createMatrixFromArray(values, 3, 3);

    transposeSquareMatrix(&testMatrix);

    int expectedValues[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};

    for (int i = 0; i < testMatrix.nRows; ++i) {
        for (int j = 0; j < testMatrix.nCols; ++j) {
            assert(testMatrix.values[i][j] == expectedValues[i * testMatrix.nCols + j]);
        }
    }

    freeMemMatrix(&testMatrix);
}

void testTransposeMatrix() {
    int values[] = {1, 2, 3, 4, 5, 6};
    matrix testMatrix = createMatrixFromArray(values, 2, 3);

    transposeMatrix(&testMatrix);

    int expectedValues[] = {1, 4, 2, 5, 3, 6};

    for (int i = 0; i < testMatrix.nRows; ++i) {
        for (int j = 0; j < testMatrix.nCols; ++j) {
            assert(testMatrix.values[i][j] == expectedValues[i * testMatrix.nCols + j]);
        }
    }

    freeMemMatrix(&testMatrix);
}

void test() {
    testSwap();
    testSortFunctions();
    testAreTwoMatricesEqual();
    testGetMinAndMaxValuePos();
    testIsEMatrix();
    testIsSymmetricMatrix();
    testIsSquareMatrix();
    testTransposeMatrix();
    testTransposeSquareMatrix();
    
}

int main() {
    test();

    printf("Tests Passed");
    return 0;
}
