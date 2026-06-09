# ============================================================
# Makefile - Airport Passenger Service System
# ============================================================

CXX     = g++
CXXFLAGS = -std=c++11 -Wall -pthread
TARGET  = airport_system
SRCS    = main.cpp queue_module.cpp stack_module.cpp dc_module.cpp parallel_module.cpp
OBJS    = $(SRCS:.cpp=.o)

# Default target: compile everything
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "=== Kompilasi berhasil! Jalankan: ./$(TARGET) ==="

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "=== File kompilasi dihapus. ==="

# Rebuild from scratch
rebuild: clean all

# Compile tanpa Makefile (manual, jika make tidak tersedia)
manual:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
	@echo "=== Kompilasi manual selesai. ==="

.PHONY: all clean rebuild manual
