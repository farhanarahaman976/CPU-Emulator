#Week 8: Performance Optimization
##Objective: Optimize the emulator for better performance.

###Tasks & Breakdown

**1. Profile the Emulator to Identify Bottlenecks**
- **Set Up Profiling Tools**: Use a profiler such as gprof, Valgrind, or Perf to analyze your C++ code.
- **Measure Performance**: Run the emulator with test cases to gather data on execution time, memory usage, and CPU cycles.
- **Identify Hotspots**: Look for functions or code sections consuming the most resources (e.g., frequent loops, memory allocation, or intensive arithmetic operations).
- **Document Findings**: Create a list of identified bottlenecks and prioritize them for optimization.

**2. Optimize Critical Code Paths**
- **Focus on Hotspots**: Rewrite or optimize the identified bottlenecks from the profiling results.
- **Techniques to Apply**:
 - **Minimize Memory Access**: Reduce redundant memory reads/writes and use caching where possible.
 - **Inline Functions**: Replace small, frequently used functions with inline code for faster execution.
 - **Efficient Data Structures**: Use STL containers like ``std::vector`` or ``std::unordered_map`` for better performance.
 - **Algorithm Optimization**: Replace inefficient algorithms with more optimal ones (e.g., O(n^2) → O(n log n)).
- **Testing & Validation**: After every optimization, test thoroughly to ensure no functionality is broken.

**3. Enhance the Assembler for Better Instruction Encoding**
- **Implement Efficient Encoding**: Review your instruction formats and optimize how they are converted into machine code.
 - Use compact encoding to minimize instruction size.
 - Align instructions to reduce CPU overhead.
- **Optimize Parsing**: Ensure the assembler parses assembly code quickly with optimized string/token manipulation techniques.
- **Error Handling Improvements**: Streamline the error-checking code to make debugging faster.
- **Add Caching**: Cache frequently used instructions or labels for reuse.

