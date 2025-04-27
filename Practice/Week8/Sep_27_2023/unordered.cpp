#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

int main()
{
    std::unordered_map<std::string, int> scores;

    scores["Alice"] = 90;
    scores["Bob"] = 85;
    scores["Eve"] = 88;

    // Load Factor (LF) = Number of Elements / Number of Buckets
    double maxLoadFactor = scores.max_load_factor();
    std::cout << "Max Load Factor: " << maxLoadFactor << std::endl;
    scores.max_load_factor(0.7);

    double currentLoadFactor = scores.load_factor();
    std::cout << "Current Load Factor: " << currentLoadFactor << std::endl;

    std::string keyToFind = "Bob";
    size_t bucketNumber = scores.bucket(keyToFind);
    std::cout << "Bucket Number for '" << keyToFind << "': " << bucketNumber << std::endl;

    auto bucketBegin = scores.begin(bucketNumber);
    auto bucketEnd = scores.end(bucketNumber);
    std::cout << "Elements in Bucket " << bucketNumber << ":" << std::endl;
    for (auto it = bucketBegin; it != bucketEnd; ++it)
    {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }

    size_t numBuckets = scores.bucket_count();
    std::cout << "Number of Buckets: " << numBuckets << std::endl;

    size_t elementsInBucket = scores.bucket_size(bucketNumber);
    std::cout << "No of Elements in Bucket " << bucketNumber << ": " << elementsInBucket << std::endl;

    size_t newBucketCount = 10;
    scores.rehash(newBucketCount);

    size_t numBucketsToReserve = 20;
    scores.reserve(numBucketsToReserve);

    auto hashFn = scores.hash_function();
    auto keyEqualFn = scores.key_eq();

    // Hash a key using the hash function
    std::string keyToHash = "Alice";
    size_t hashValue = hashFn(keyToHash);
    std::cout << "Hash value for '" << keyToHash << "': " << hashValue << std::endl;

    // Compare keys using the key equality comparison function
    std::string key1 = "Alice";
    std::string key2 = "Bob";
    bool keysAreEqual = keyEqualFn(key1, key2);
    std::cout << "Are keys '" << key1 << "' and '" << key2 << "' equal? " << (keysAreEqual ? "Yes" : "No") << std::endl;

    //
    //
    std::unordered_set<int> mySet;
    std::unordered_set<int> mySet2{{41, 42, 43, 44}};
    mySet.insert(41);
    mySet.insert(42);
    mySet.insert(43);
    mySet.insert(44);
    if (mySet2 == mySet) // only with set
    {
        std::cout << "equal set" << std::endl;
    }

    return 0;
}
