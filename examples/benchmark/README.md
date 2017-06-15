# Benchmark

Using `std::chrono`this example measures processing times of libtssi2 compares to:

```c++
void read(span<const char> data) {
	for (auto v : data) {}
}
```

Only the time spent in libtssi2 or `read`is measured. Disc to memory transfers are omitted. Data is processed in 1MB chunks.

![libtssi benchmark](./benchmark.png)

All tests were conducted on a HP Spectre x360 with Intel Core i7-7500U. 