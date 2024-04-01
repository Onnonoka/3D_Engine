#include <vector>

typedef long DirtyField;

/**
 * @brief Represents a dirty flag manager to track changes in multiple flags.
 * 
 * This class provides functionality to manage multiple dirty flags efficiently using bit manipulation.
 */
class Dirty {
public:
    /**
     * @brief Default constructor for the Dirty class.
     * Initializes the dirty flags to zero.
     */
    Dirty();

    /**
     * @brief Checks if any of the dirty flags are set.
     * 
     * @return True if any of the dirty flags are set, false otherwise.
     */
    bool isDirty() const;

    /**
     * @brief Checks if a specific dirty flag is set.
     * 
     * @param index The index of the dirty flag to check.
     * @return True if the dirty flag at the specified index is set, false otherwise.
     */
    bool isDirty(const unsigned int index) const;
    
    /**
     * @brief Resets all dirty flags to clean state.
     */
    void cleanDirtyFlags();

    /**
     * @brief Resets a specific dirty flag to clean state.
     * 
     * @param index The index of the dirty flag to clean.
     */
    void cleanDirtyFlag(const unsigned int index);

protected:
    /**
     * @brief Sets all dirty flags to dirty state.
     */
    void makeDirty();
    
    /**
     * @brief Sets a specific dirty flag to dirty state.
     * 
     * @param index The index of the dirty flag to set.
     */
    void makeDirty(const unsigned int index);

    /**
     * @brief Retrieves the dirty flags.
     * 
     * @return The dirty flags.
     */
    DirtyField getDirtyFlags() const;

private:
    DirtyField dirtyFlags; ///< Bitset representing the dirty flags.
};