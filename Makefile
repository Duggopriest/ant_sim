all:
	clang++ main.c -o run

git:
	@clear
	@git add .
	@echo "commit msg" 
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

REPO = git@github.com:Duggopriest/ant_sim.git

gitset:
	echo "# ant_sim" >> README.md
	git init
	git add README.md
	git commit -m "first commit"
	git branch -M main
	git remote add origin $(REPO)
	git push -u origin main

test:
	@echo working