INPUT ?=

setup:
	cp -r ./template/ ./src/

run:
ifeq ($(strip $(INPUT)),)
	@./problem.out
else
	@./problem.out < $(INPUT)
endif


clean:
	rm -rf ./src
	rm -rf ./problem.out
