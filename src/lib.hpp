#pragma once

/// Return non-random number
extern int not_random();

/// Some struct
/**
 * Does something unknown
 */
struct S {
    int a; ///< int field

    /// float field
    float b;

    /**
     * \brief Set all
     *
     * Sets all fields
     * \param a int field
     * \param b float field
     * \return nothing
     */
    void set(int a, int b);
};
