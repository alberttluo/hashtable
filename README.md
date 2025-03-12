# A Simple Hash Table Implementation

## Design Process

A hash table is a data structure designed for efficient data storage and retrieval. It achieves constant-time complexity (on average) for search, insertion, and deletion operations through the use of hashing. Hashing transforms keys into array indices, ideally distributing keys uniformly to minimize collisions.

The primary factors influencing a hash table’s performance are:

### 1. **Hash Function**
The choice of hash function significantly impacts performance. A good hash function uniformly distributes keys to minimize collisions. Common methods include modular arithmetic and multiplicative hashing. The provided hash table uses a multiplicative hashing function combined with bitwise operations to evenly distribute integer keys.

### 2. **Collision Resolution Methods**
Collisions occur when different keys map to the same index. The two common methods are:

- **Chaining**:
  - Each bucket in the hash table contains a linked list.
  - New entries are inserted at the beginning of the list.
  - Searches traverse the linked list.

- **Linear Probing**:
  - When a collision occurs, the hash table checks subsequent indices (linearly) until an empty bucket is found.
  - Can suffer from clustering issues, negatively affecting performance if not carefully managed.

This hash table implementation employs **chaining**, making collision resolution straightforward but potentially slower if the lists become excessively long.

### 2. **Load Factor**
- Defined as the ratio of the number of stored items (`size`) to the number of buckets (`capacity`).
- Typically, resizing occurs once a specific load factor threshold (e.g., 0.7) is surpassed.
- Maintaining an appropriate load factor ensures efficient performance by reducing the average chain length.

### 3. **Resizing**
- When resizing is required (load factor exceeded), the hash table capacity is doubled.
- All existing entries are rehashed and redistributed into the new, larger table.
- Resizing involves memory reallocation and rehashing all elements, which is relatively costly but occurs infrequently.

### 3. **Probing Strategy**
- Although this implementation primarily uses chaining, linear probing could be considered an alternative method for collision resolution:
  - **Linear probing** increments indices sequentially until a free slot is found.
  - Provides faster locality of reference but increases sensitivity to clustering.
