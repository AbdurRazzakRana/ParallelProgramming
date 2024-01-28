# Introduction
In the realm of computing, where diverse platforms offer parallelism, a thorough evaluation becomes imperative. Testing these platforms with various datasets is a crucial step in discerning their capabilities. This multifaceted assessment involves subjecting each platform to rigorous scrutiny to analyze their performance under distinct conditions. Finally, by meticulously gauging the runtime intricacies, one can make an informed decision on the optimal platform for specific purposes. This comprehensive evaluation ensures that the chosen platform aligns seamlessly with the intended tasks, maximizing efficiency and performance in parallel processing scenarios.

# Platforms Evaluated: 
Cuda, OpenMP, MPI with Cluter of Servers, Java, C with Threads

# Preparing Input:
1. For each size of input, one input file will be generated, and the exact file will be tested to 5 different algorithms to make them feel the same completely to compare proper runtime.
2. Therefore, before running every algorithm, generating3 file will be run once.
   ./generate3 10000 2 4
   
   Here, the first argument is the size of the array, and the next values are the range of integers that the array will have. 2 is the lower bound and 4 is the upper bound. Therefore, this array will have 10,000 integers and all of them are between 2 and 4. Also, the number of serial counts is taken to compare with parallel algorithms. 
Here, 3256 number of times the three is in the array.
