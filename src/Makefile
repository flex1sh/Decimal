NAME_IMAGE		=s21_$(shell  grep FROM Dockerfile|sed 's|:.*||'|sed 's|.*/||'|sed 's|.* ||')
NAME_CONTAINER	=$(NAME_IMAGE)
TEST_PATH		=testing

SOURCES			=$(shell find ./ -name 's21_*.c')

all: start_cs

# mcs decimal_convert.cs && mono decimal_convert.exe | tee convert.log && rm decimal_convert.exe

s21_decimal.a: $(SOURCES)
	gcc $(FLAGS) -c $^ -lm
	ar rc $@ s21*.o
	rm -rf s21*.o
	ranlib $@

test: s21_decimal.a start_cs
	cd $(TEST_PATH) && gcc test_dec.c -o $@ && ./$@ | tee $@.log && rm $@


# При первом запуска конвертера
docker_first: docker_build docker_run

docker_build:
	docker build -t $(NAME_IMAGE) -f ./$(TEST_PATH)/Dockerfile .
docker_run:
	# docker run --name $(NAME_CONTAINER) --rm -i -t -v $(shell pwd):/s21_home $(NAME_IMAGE)
	docker run --name $(NAME_CONTAINER) --rm -d -t -v $(shell pwd):/s21_home $(NAME_IMAGE)
	# docker exec -it $(NAME_CONTAINER) cd $(TEST_PATH)
	# 2>/dev/null || true

in_container:
	docker exec -it $(NAME_CONTAINER) bash

docker_stop:
	docker stop $(NAME_CONTAINER) || true

docker_rm: docker_stop
	docker rmi $(NAME_IMAGE) || true

# start_cs - запуск конвертера. Числа записывать в src/number.txt; 
# Поддерживат: "123 + 456" "321 - 654" "INT_MAX" "INT_MIN - 1" "MAX - MIN" "MIN"
# Математические операции: + - / * %
# Знаки математических операций обрамляются пробелами: " + "
# Строка начинающаяся с // считается комментарием
start_cs:
	docker exec -it $(NAME_CONTAINER) mcs $(TEST_PATH)/decimal_convert.cs 
	docker exec -it $(NAME_CONTAINER) mono $(TEST_PATH)/decimal_convert.exe>$(TEST_PATH)/convert.log
	cat $(TEST_PATH)/convert.log
	@docker exec -it $(NAME_CONTAINER) rm $(TEST_PATH)/decimal_convert.exe

clean:
	rm -rf convert.log decimal_convert.exe *.out *.gch *.log */*.log