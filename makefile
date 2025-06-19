# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -g

# Directorios
SRCDIR = src
OBJDIR = build

# Archivos objeto (van a build/)
OBJS = $(OBJDIR)/main.o $(OBJDIR)/Process.o $(OBJDIR)/Scheduler.o $(OBJDIR)/utils.o $(OBJDIR)/users.o $(OBJDIR)/ProcessManager.o $(OBJDIR)/Logger.o $(OBJDIR)/filesystem.o

# Ejecutable final
TARGET = UpSystemExecute

# Regla principal
all: mkdirs $(TARGET)

# Crea carpetas necesarias
mkdirs:
	mkdir -p data logs $(OBJDIR)

# Link final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Reglas para compilar cada archivo .cpp a .o
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/Scheduler.h $(SRCDIR)/Process.h $(SRCDIR)/users.h $(SRCDIR)/ProcessManager.h $(SRCDIR)/Logger.h $(SRCDIR)/filesystem.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/Process.o: $(SRCDIR)/Process.cpp $(SRCDIR)/Process.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Process.cpp -o $(OBJDIR)/Process.o

$(OBJDIR)/Scheduler.o: $(SRCDIR)/Scheduler.cpp $(SRCDIR)/Scheduler.h $(SRCDIR)/Process.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Scheduler.cpp -o $(OBJDIR)/Scheduler.o

$(OBJDIR)/utils.o: $(SRCDIR)/utils.cpp $(SRCDIR)/utils.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/utils.cpp -o $(OBJDIR)/utils.o

$(OBJDIR)/users.o: $(SRCDIR)/users.cpp $(SRCDIR)/users.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/users.cpp -o $(OBJDIR)/users.o

$(OBJDIR)/ProcessManager.o: $(SRCDIR)/ProcessManager.cpp $(SRCDIR)/users.h $(SRCDIR)/ProcessManager.h $(SRCDIR)/Logger.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/ProcessManager.cpp -o $(OBJDIR)/ProcessManager.o

$(OBJDIR)/Logger.o: $(SRCDIR)/Logger.cpp $(SRCDIR)/Logger.h     
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Logger.cpp -o $(OBJDIR)/Logger.o

$(OBJDIR)/filesystem.o: $(SRCDIR)/filesystem.cpp $(SRCDIR)/filesystem.h $(SRCDIR)/Logger.h  
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/filesystem.cpp -o $(OBJDIR)/filesystem.o

# Limpiar
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
