NAME_IMAGE		=s21_$(shell  grep FROM Dockerfile|sed 's|:.*||'|sed 's|.*/||'|sed 's|.* ||')
NAME_CONTAINER	=$(NAME_IMAGE)

all: start_cs

# mcs decimal_convert.cs && mono decimal_convert.exe | tee convert.log && rm decimal_convert.exe


# При первом запуска конвертера
doker_first: docker_build docker_run

docker_build: Dockerfile
	docker build -t $(NAME_IMAGE) .
docker_run:
	# docker run --name $(NAME_CONTAINER) --rm -i -t -v $(shell pwd):/s21_home $(NAME_IMAGE)
	docker run --name $(NAME_CONTAINER) --rm -d -t -v $(shell pwd):/s21_home $(NAME_IMAGE)
	# docker exec -it $(NAME_CONTAINER) cd testing
	# 2>/dev/null || true

in_container:
	docker exec -it $(NAME_CONTAINER) bash

docker_stop:
	docker stop $(NAME_CONTAINER) || true

docker_rm: docker_stop
	docker rmi $(NAME_IMAGE) || true

# Запуск конвертера. числа записывать в src/number.txt; 
# Поддерживат: "ADD 123 456" "SUB 321 654" "INT_MAX" "INT_MIN" "MAX" "MIN"
start_cs:
	docker exec -it $(NAME_CONTAINER) mcs testing/decimal_convert.cs 
	docker exec -it $(NAME_CONTAINER) mono testing/decimal_convert.exe>testing/convert.log
	cat testing/convert.log
	@docker exec -it $(NAME_CONTAINER) rm testing/decimal_convert.exe

clean:
	rm -rf convert.log decimal_convert.exe *.out *.gch