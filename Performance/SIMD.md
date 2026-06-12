# SIMD
- [Algorithmic Patterns](#algorithmic-patterns)

## Links <!-- omit from toc -->


## Algorithmic Patterns
- **Tree Fold:**
  - condense array of vector registers to a single vector register (vertical reduction)
  - by repeatedly combining adjacent register pairs in a tree-like structure
  - ```cpp
    // ============================================================================
    // assume vec_array = [V0, V1, V2, V3]
    // iteration 1 (stride = 1):
    //     V0 = v_add(V0, V1)
    //     V2 = v_add(V2, V3)
    // iteration 2 (stride = 2):
    //     V0 = v_add(V0, V2)
    // final result is consolidated into V0.
    // ============================================================================

    Vector tree_fold(Vector* vec_array, int num_vectors) {
        // outer loop dictates the step/stride size, doubling each time
        for (int stride = 1; stride < num_vectors; stride *= 2) {
            // inner loop pairs up adjacent vectors based on the current stride
            for (int i = 0; i < num_vectors; i += 2 * stride) {
                vec_array[i] = v_add(vec_array[i], vec_array[i + stride]);
            }
        }
        // single consolidated vector register
        return vec_array[0];
    }
    ```
- **Butterfly Fold:**
  - reduce a vector register down to a scalar value (horizontal reduction)
  - by repeatedly rotating register's lanes by half and combining it with itself
  - rotate + combine is done `log2(num_lanes)` times
  - ```cpp
    // ============================================================================
    // assume each vector has 4 lanes: V = [A, B, C, D]
    // iteration 1 (offset = 4 / 2 = 2):
    //     rotated = vrotate(V, 2)   ->   [C, D, A, B]
    //     V = v_add(V, rotated)     ->   [A+C, B+D, C+A, D+B]
    // iteration 2 (offset = 2 / 2 = 1):
    //     rotated = vrotate(V, 1)   ->   [B+D, C+A, D+B, A+C]
    //     V = v_add(V, rotated)     ->   [A+C+B+D, B+D+C+A, C+A+D+B, D+B+A+C]
    // every lane now contains the fully reduced scalar sum: (A + B + C + D)
    // ============================================================================

    Scalar butterfly_fold(Vector v) {
        // shifting by half the total number of lanes, halving the offset each step down to 1
        for (int offset = NUM_LANES / 2; offset > 0; offset /= 2) {
            Vector rotated = vrotate(v, offset);
            v = v_add(v, rotated);
        }
        // return final accumulated scalar (same value in all lanes)
        return v[0];
    }
    ```