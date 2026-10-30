CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -MMD -MP

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

adec: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o adec

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

PROGRAMS := $(basename $(wildcard ../playground/*.adel))

test: adec
	@for p in $(PROGRAMS); do \
		echo "--- $$p.adel"; \
		./adec $$p.adel -o $$p && $$p; \
	done

clean:
	rm -f adec $(OBJS) $(DEPS)

.PHONY: test clean

-include $(DEPS)
