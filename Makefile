DIR=src/

all: 
	$(MAKE) -C $(DIR) all

debug:
	$(MAKE) -c $(DIR) debug

clean:
	$(MAKE) -C $(DIR) clean

link:
	$(MAKE) -C $(DIR) link