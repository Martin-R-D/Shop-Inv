CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = shop

SRCS = main.cpp Person.cpp Admin.cpp Cashier.cpp Supplier.cpp \
       Product.cpp PhysicalProduct.cpp ServiceProduct.cpp \
       Category.cpp Discount.cpp PercentDiscount.cpp \
       Transaction.cpp TransactionItem.cpp Delivery.cpp Store.cpp \
	   FileManager.cpp FixedDiscount.cpp AuthManager.cpp ReportManager.cpp \
	   MenuHelpers.cpp InputValidator.cpp SampleData.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	@if defined OS (if "$(OS)"=="Windows_NT" (del /F /Q $(OBJS) $(TARGET)) else (rm -f $(OBJS) $(TARGET))) else (rm -f $(OBJS) $(TARGET))

.PHONY: clean