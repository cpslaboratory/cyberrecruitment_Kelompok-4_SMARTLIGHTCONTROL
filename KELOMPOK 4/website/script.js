const header = document.querySelector("header");

/*----------------- Sticky Navbar --------------------*/
function stickyNavbar() {
    header.classList.toggle("scrolled", window.pageYOffset > 0);
}

stickyNavbar();

window.addEventListener("scroll", stickyNavbar);

/*----------------- Scroll Reveal --------------------*/

let sr = ScrollReveal({
    duration: 2500,
    distance: "60px",
});

sr, reveal(".showcase-info", { delay: 600 });
sr, reveal(".showcase-images", { origin: "top", delay: 600 });