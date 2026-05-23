// Smooth scroll для навигации
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
            target.scrollIntoView({ behavior: 'smooth', block: 'start' });
        }
    });
});

// Анимация при прокрутке страницы
const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -100px 0px'
};

const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
        if (entry.isIntersecting) {
            entry.target.style.opacity = '1';
            entry.target.style.transform = 'translateY(0)';
        }
    });
}, observerOptions);

document.querySelectorAll('.feature-card, .category, .stat').forEach(el => {
    el.style.opacity = '0';
    el.style.transform = 'translateY(30px)';
    el.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
    observer.observe(el);
});

// Обработка кликов на кнопки
document.querySelectorAll('.btn').forEach(btn => {
    btn.addEventListener('click', function() {
        // Добавляем эффект клика
        const ripple = document.createElement('span');
        ripple.style.position = 'absolute';
        ripple.style.borderRadius = '50%';
        ripple.style.background = 'rgba(255, 255, 255, 0.6)';
        ripple.style.width = '20px';
        ripple.style.height = '20px';
        ripple.style.pointerEvents = 'none';
        
        this.style.position = 'relative';
        this.style.overflow = 'hidden';
        
        const rect = this.getBoundingClientRect();
        const size = Math.max(rect.width, rect.height);
        
        ripple.style.width = size + 'px';
        ripple.style.height = size + 'px';
        ripple.style.animation = 'ripple 0.6s ease-out';
        
        this.appendChild(ripple);
        
        setTimeout(() => ripple.remove(), 600);
    });
});

// Добавляем CSS для ripple анимации
const style = document.createElement('style');
style.textContent = `
    @keyframes ripple {
        from {
            opacity: 1;
            transform: scale(0);
        }
        to {
            opacity: 0;
            transform: scale(1);
        }
    }
`;
document.head.appendChild(style);

// Обработка активной навигации при скролле
window.addEventListener('scroll', () => {
    const sections = document.querySelectorAll('section');
    const navLinks = document.querySelectorAll('.nav-links a:not(.cta-btn)');
    
    let current = '';
    sections.forEach(section => {
        const sectionTop = section.offsetTop;
        if (scrollY >= sectionTop - 200) {
            current = section.getAttribute('id');
        }
    });
    
    navLinks.forEach(link => {
        link.classList.remove('active');
        if (link.getAttribute('href') === '#' + current) {
            link.style.color = 'var(--primary-color)';
        } else {
            link.style.color = 'var(--text-color)';
        }
    });
});

// Функция для отправки на регистрацию
function startGaming() {
    const modal = document.createElement('div');
    modal.style.cssText = `
        position: fixed;
        top: 0;
        left: 0;
        width: 100%;
        height: 100%;
        background: rgba(0, 0, 0, 0.8);
        display: flex;
        align-items: center;
        justify-content: center;
        z-index: 2000;
    `;
    
    modal.innerHTML = `
        <div style="
            background: #1a1a1a;
            border: 2px solid #00d4ff;
            border-radius: 10px;
            padding: 40px;
            max-width: 500px;
            width: 90%;
        ">
            <h2 style="color: #00d4ff; margin-bottom: 20px;">Присоединиться к Nexus</h2>
            
            <form onsubmit="handleRegistration(event)">
                <div style="margin-bottom: 15px;">
                    <input type="text" placeholder="Имя пользователя" required 
                        style="width: 100%; padding: 10px; background: #0a0a0a; 
                               border: 1px solid #2a2a2a; color: white; border-radius: 5px;">
                </div>
                
                <div style="margin-bottom: 15px;">
                    <input type="email" placeholder="Электронная почта" required
                        style="width: 100%; padding: 10px; background: #0a0a0a; 
                               border: 1px solid #2a2a2a; color: white; border-radius: 5px;">
                </div>
                
                <div style="margin-bottom: 20px;">
                    <input type="password" placeholder="Пароль" required
                        style="width: 100%; padding: 10px; background: #0a0a0a; 
                               border: 1px solid #2a2a2a; color: white; border-radius: 5px;">
                </div>
                
                <button type="submit" style="
                    width: 100%;
                    padding: 12px;
                    background: linear-gradient(135deg, #00d4ff 0%, #ff006e 100%);
                    color: black;
                    border: none;
                    border-radius: 5px;
                    font-weight: bold;
                    cursor: pointer;
                    font-size: 1em;
                ">Зарегистрироваться</button>
                
                <button type="button" onclick="this.closest('div').parentElement.remove()" style="
                    width: 100%;
                    padding: 10px;
                    margin-top: 10px;
                    background: transparent;
                    color: #00d4ff;
                    border: 1px solid #00d4ff;
                    border-radius: 5px;
                    cursor: pointer;
                ">Отмена</button>
            </form>
        </div>
    `;
    
    document.body.appendChild(modal);
}

function handleRegistration(event) {
    event.preventDefault();
    alert('✓ Регистрация успешна! Добро пожаловать в Nexus Cloud Gaming!');
    event.target.closest('div').parentElement.remove();
}

// Привязываем кнопки регистрации к функции
document.querySelectorAll('.btn-primary, .cta-btn').forEach(btn => {
    if (btn.textContent.includes('игр') || btn.textContent.includes('Начать') || btn.textContent.includes('Присоединиться')) {
        btn.addEventListener('click', startGaming);
    }
});

// Particula эффект для фона (опционально)
function createParticles() {
    const canvas = document.createElement('canvas');
    canvas.style.cssText = `
        position: fixed;
        top: 0;
        left: 0;
        width: 100%;
        height: 100vh;
        pointer-events: none;
        z-index: 1;
    `;
    
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
    
    document.body.insertBefore(canvas, document.body.firstChild);
    
    const ctx = canvas.getContext('2d');
    const particles = [];
    
    class Particle {
        constructor() {
            this.x = Math.random() * canvas.width;
            this.y = Math.random() * canvas.height;
            this.size = Math.random() * 2 + 1;
            this.speedX = Math.random() * 0.5 - 0.25;
            this.speedY = Math.random() * 0.5 - 0.25;
            this.opacity = Math.random() * 0.5 + 0.2;
        }
        
        update() {
            this.x += this.speedX;
            this.y += this.speedY;
            
            if (this.x < 0) this.x = canvas.width;
            if (this.x > canvas.width) this.x = 0;
            if (this.y < 0) this.y = canvas.height;
            if (this.y > canvas.height) this.y = 0;
        }
        
        draw() {
            ctx.fillStyle = `rgba(0, 212, 255, ${this.opacity})`;
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2);
            ctx.fill();
        }
    }
    
    for (let i = 0; i < 50; i++) {
        particles.push(new Particle());
    }
    
    function animate() {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        
        particles.forEach(p => {
            p.update();
            p.draw();
        });
        
        requestAnimationFrame(animate);
    }
    
    animate();
    
    window.addEventListener('resize', () => {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
    });
}

// Инициализация частиц при загрузке
document.addEventListener('DOMContentLoaded', () => {
    // createParticles(); // Раскомментируй для включения фонового эффекта
});

// Логирование в консоль
console.log('%c Nexus Cloud Gaming ', 
    'background: linear-gradient(135deg, #00d4ff 0%, #ff006e 100%); ' +
    'color: black; ' +
    'font-weight: bold; ' +
    'padding: 10px 20px; ' +
    'border-radius: 5px;'
);
console.log('%c Революция в облачном гейминге! ', 
    'color: #00d4ff; ' +
    'font-size: 14px; ' +
    'font-weight: bold;'
);
