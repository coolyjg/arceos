REDIS_PATH := $(PWD)/redis

clean:
	$(MAKE) -C $(REDIS_PATH) clean
	$(MAKE) -C $(REDIS_PATH)/deps/hdr_histogram/ clean
	$(MAKE) -C $(REDIS_PATH)/deps/hiredis/ clean
	$(MAKE) -C $(REDIS_PATH)/deps/lua/src/ clean
	rm -f redis/src/redis-server.o
	rm -f *.o
	rm -f *.a
	rm -f $(REDIS_PATH)/src/.make-settings
	rm -f $(REDIS_PATH)/src/.make-prerequisites

.PHONY: clean
